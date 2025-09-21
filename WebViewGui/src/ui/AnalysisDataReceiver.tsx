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
  return dividend - Math.floor(dividend / divisor) * divisor;
}

// Frame 타입 정의
interface FrameData {
  timeMs: number;
  values: number[];
}

export default class AnalysisDataReceiver {
  public bufferLength: number;

  public buffer: FrameData[];

  public readIndex: number;

  public writeIndex: number;

  public lastTimeStampMs: number;

  public timeResolutionMs: number;

  public outputNumChannels: number;

  public analysisDataRegistrationId: string;

  constructor(bufferLength: number) {
    this.bufferLength = bufferLength;
    this.buffer = new Array(this.bufferLength);
    this.readIndex = 0;
    this.writeIndex = 0;
    this.lastTimeStampMs = 0;
    this.timeResolutionMs = 0;
    this.outputNumChannels = 0;

    // eslint-disable-next-line @typescript-eslint/no-this-alias
    const self = this;

    // 이벤트 리스너 등록
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

            self.outputNumChannels = data.outputNumChannels;

            if (self.timeResolutionMs === 0) {
              self.timeResolutionMs = data.timeResolutionMs;
              self.readIndex = 0;
              self.buffer.fill({
                timeMs: 0,
                values: new Array(data.frames[0].values.length).fill(0),
              });
            }

            // eslint-disable-next-line promise/always-return
            for (const f of data.frames) {
              self.buffer[mod(self.writeIndex++, self.bufferLength)] = f;
            }
          })
          // eslint-disable-next-line no-console
          .catch(console.error);
      }
    );
  }

  getOutputNumChannels() {
    return this.outputNumChannels;
  }

  getBufferItem(index: number) {
    return this.buffer[mod(index, this.buffer.length)];
  }

  // timestamp 기반 보간
  getLevels(timeStampMs: number) {
    if (this.writeIndex === 0) return this.buffer[0]?.values;

    const latestWrite = this.writeIndex - 1;

    // prev/next frame 찾기
    let prevFrame = this.getBufferItem(0);
    let nextFrame = prevFrame;

    for (let i = 0; i <= latestWrite; i++) {
      const frame = this.getBufferItem(i);
      if (frame.timeMs <= timeStampMs) prevFrame = frame;
      if (frame.timeMs > timeStampMs) {
        nextFrame = frame;
        break;
      }
    }

    const dt = nextFrame.timeMs - prevFrame.timeMs;
    const s = dt > 0 ? (timeStampMs - prevFrame.timeMs) / dt : 0;

    return interpolate(prevFrame.values, nextFrame.values, s);
  }

  unregister() {
    // eslint-disable-next-line @typescript-eslint/ban-ts-comment
    // @ts-ignore
    // eslint-disable-next-line no-underscore-dangle
    window.__JUCE__.backend.removeEventListener(this.analysisDataRegistrationId);
  }
}
