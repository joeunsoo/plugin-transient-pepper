'use client';

import { useEffect, useRef, useState } from 'react';

import AnalysisDataReceiver from '@/ui/AnalysisDataReceiver';

import Box from '@mui/material/Box';

export default function FreqBandInfo() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  let dataReceiver: AnalysisDataReceiver | null = null;
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

    if (isActive) {
      window.requestAnimationFrame(render);
    }
  };

  useEffect(() => {
    // eslint-disable-next-line react-hooks/exhaustive-deps
    dataReceiver = new AnalysisDataReceiver(10);
    setIsActive(true);
    window.requestAnimationFrame(render);

    return function cleanup() {
      setIsActive(false);
      dataReceiver?.unregister();
    };
  }, []);

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
    <Box
      sx={{
        '& .value': {
          position: 'absolute',
          left: 0,
          top: 0,
          width: '100%',
          backgroundColor: '#ff0000'
        }
      }}
    >
      {/* eslint-disable */}
      {/* @ts-ignore */}
      <canvas height={90} style={canvasStyle} ref={canvasRef}></canvas>
    </Box>
  );
}