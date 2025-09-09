'use client';

import { useEffect, useRef, useState } from 'react';
import * as Juce from 'juce-framework-frontend';

import { SpectrumDataReceiverEventId } from '@/define';

import Box from '@mui/material/Box';

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

class SpectrumDataReceiver {
  public bufferLength: number;

  public buffer: number[][];

  public readIndex: number;

  public writeIndex: number;

  public lastTimeStampMs: number;

  public timeResolutionMs: number;

  public spectrumDataRegistrationId: string;

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
    this.spectrumDataRegistrationId = window.__JUCE__.backend.addEventListener(
      SpectrumDataReceiverEventId,
      () => {
        fetch(Juce.getBackendResourceAddress('spectrumData.json'))
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
      this.spectrumDataRegistrationId
    );
  }
}

export default function FreqBandInfo() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  let dataReceiver: SpectrumDataReceiver | null = null;
  const [isActive, setIsActive] = useState<boolean>(true);

  const render = (timeStampMs: number) => {
    const canvas = canvasRef.current;
    if (canvas) {
      const ctx = canvas.getContext('2d');
      if (ctx) {
        ctx.clearRect(0, 0, canvas.width, canvas.height);

        const grd = ctx.createLinearGradient(0, 0, 0, canvas.height);
        grd.addColorStop(0, '#1976d2');
        grd.addColorStop(1, '#dae9f8');
        ctx.fillStyle = grd;

        if (dataReceiver != null) {
          const levels = dataReceiver.getLevels(timeStampMs);

          if (levels != null) {
            const numBars = levels.length;
            const barWidth = canvas.width / numBars;
            const barHeight = canvas.height;

            for (const [i, l] of levels.entries()) {
              ctx.fillRect(
                i * barWidth,
                barHeight - l * barHeight,
                barWidth,
                l * barHeight
              );
            }
          }
        }
      }
    }

    if (isActive) window.requestAnimationFrame(render);
  };

  useEffect(() => {
    // eslint-disable-next-line react-hooks/exhaustive-deps
    dataReceiver = new SpectrumDataReceiver(10);
    setIsActive(true);
    window.requestAnimationFrame(render);

    return function cleanup() {
      setIsActive(false);
      dataReceiver?.unregister();
    };
  });

  const canvasStyle = {
    marginLeft: '0',
    marginRight: '0',
    marginTop: '1em',
    display: 'block',
    width: '94%',
    bottom: '0',
    position: 'absolute',
  };

  return (
    <Box>
      {/* eslint-disable */}
      {/* @ts-ignore */}
      <canvas height={90} style={canvasStyle} ref={canvasRef}></canvas>
    </Box>
  );
}
