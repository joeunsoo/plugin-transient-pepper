import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import { useAnimationFrame } from 'framer-motion';
import applySkew from '@/utils/applySkew';
import { useEffect, useRef } from 'react';

interface EnvelopeGraphProps {
  idx: number
  width?: number;
  height?: number;
  fill?: string;       // 밑부분 색
}

export default function EnvelopeGraph({
  idx,
  width = 15,
  height = 100,
  fill = 'null', // 기본 반투명
}: EnvelopeGraphProps) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const bufferRef = useRef<HTMLCanvasElement>(null);
  const { motionValues } = useAnalysisDataStore();
  const lastYRef = useRef(height);
  const smoothedYRef = useRef(height); // smoothed value
  const ctxRef = useRef<CanvasRenderingContext2D | null>(null);

useEffect(() => {
  if (canvasRef.current) {
    ctxRef.current = canvasRef.current.getContext('2d');

    if (!ctxRef.current) { return; }
    ctxRef.current.lineWidth = 2;

    bufferRef.current = document.createElement('canvas');
    bufferRef.current.width = width;
    bufferRef.current.height = height;
  }
}, [height, width]);

  useAnimationFrame(() => {
    const canvas = canvasRef.current;
    const ctx = ctxRef.current;
    const buffer = bufferRef.current;
    if (!canvas || !ctx || !buffer) { return; }

    const newValue = motionValues[idx].get();
    const skewValue = applySkew(newValue, 0.0, 1.0, 0.15);

    const value = skewValue;
    const y = height - value * height;

    const alpha = 0.2;
    smoothedYRef.current = smoothedYRef.current + alpha * (y - smoothedYRef.current);
    const smoothedY = smoothedYRef.current;

    ctx.clearRect(0, 0, width, height);
    ctx.beginPath();
    ctx.moveTo(0, smoothedY);
    ctx.lineTo(width, smoothedY);
    ctx.lineTo(width, height);
    ctx.lineTo(0, height);
    ctx.closePath();

    if (fill) {
      ctx.fillStyle = fill;
      ctx.fill();
    }

    lastYRef.current = smoothedY;
  });

  return (
    <canvas ref={canvasRef} width={width} height={height} />
  );
}
