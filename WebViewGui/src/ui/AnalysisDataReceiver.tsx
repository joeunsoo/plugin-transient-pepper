'use client';

import * as Juce from 'juce-framework-frontend';

import { AnalysisDataReceiverEventId } from '@/define';

function interpolate(a: number[], b: number[], s: number) {
  const result = new Array(a.length).fill(0);

  for (const [i, val] of a.entries()) result[i] += (1 - s) * val;

  for (const [i, val] of b.entries()) result[i] += s * val;

  return result;
}

function mod(dividend: number, divisor: number) {
  const quotient = Math.floor(dividend / divisor);

  return dividend - divisor * quotient;
}

export default class AnalysisDataReceiver {
  public bufferLength: number;

  public buffer: number[][];

  public readIndex: number;

  public writeIndex: number;

  public lastTimeStampMs: number;

  public timeResolutionMs: number;

  public analysisDataRegistrationId: string;

  constructor(bufferLength: number) {
    this.bufferLength = bufferLength;
    this.buffer = new Array(this.bufferLength);
    this.readIndex = 0;
    this.writeIndex = 0;
    this.lastTimeStampMs = 0;
    this.timeResolutionMs = 0;

    // eslint-disable-next-line @typescript-eslint/no-this-alias
    const self = this;
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    // eslint-disable-next-line no-underscore-dangle
    this.analysisDataRegistrationId = window.__JUCE__.backend.addEventListener(
      AnalysisDataReceiverEventId,
      () => {
        fetch(Juce.getBackendResourceAddress('analysisData.json'))
          .then((response) => response.text())
          .then((text) => {
            const data = JSON.parse(text);

            if (self.timeResolutionMs === 0) {
              self.timeResolutionMs = data.timeResolutionMs;

              // We want to stay behind the write index by a full batch plus one
              // so that we can keep reading buffered frames until we receive the
              // new batch
              self.readIndex = -data.frames.length - 1;

              self.buffer.fill(new Array(data.frames[0].length).fill(0));
            }

            for (const f of data.frames) {
              self.buffer[mod(self.writeIndex++, self.bufferLength)] = f;
            }

            return null;
          }).catch(null);
      }
    );
  }

  getBufferItem(index: number) {
    return this.buffer[mod(index, this.buffer.length)];
  }

  getLevels(timeStampMs: number) {
    if (this.timeResolutionMs === 0) return null;

    const previousTimeStampMs = this.lastTimeStampMs;
    this.lastTimeStampMs = timeStampMs;

    if (previousTimeStampMs === 0) return this.buffer[0];

    const timeAdvance =
      (timeStampMs - previousTimeStampMs) / this.timeResolutionMs;
    this.readIndex += timeAdvance;

    const integralPart = Math.floor(this.readIndex);
    const fractionalPart = this.readIndex - integralPart;

    return interpolate(
      this.getBufferItem(integralPart),
      this.getBufferItem(integralPart + 1),
      fractionalPart
    );
  }

  unregister() {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    // eslint-disable-next-line no-underscore-dangle
    window.__JUCE__.backend.removeEventListener(
      this.analysisDataRegistrationId
    );
  }
}
