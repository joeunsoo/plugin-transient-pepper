import { useEffect, useRef } from 'react';
import { useAnimationFrame } from 'framer-motion';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import applySkew from '@/utils/applySkew';

interface EnvelopeGraphProps {
  idx: number;
  width?: number;
  height?: number;
  fill?: string; // 밑부분 색
}

export default function EnvelopeGraph({ idx, width = 1, height = 10, fill }: EnvelopeGraphProps) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const bufferRef = useRef<HTMLCanvasElement | null>(null);
  const { motionValues } = useAnalysisDataStore();
  const smoothedYRef = useRef(height); // smoothed value
  const ctxRef = useRef<CanvasRenderingContext2D | null>(null);

  // 초기화
  useEffect(() => {
    if (!canvasRef.current) return;
    const ctx = canvasRef.current.getContext('2d');
    if (!ctx) return;

    ctx.lineWidth = 2;
    ctxRef.current = ctx;

    // 버퍼 캔버스 초기화
    const buffer = document.createElement('canvas');
    buffer.width = width;
    buffer.height = height;
    bufferRef.current = buffer;
  }, [width, height]);

  useAnimationFrame(() => {
    const ctx = ctxRef.current;
    if (!ctx) return;

    const newValue = motionValues[idx]?.get() ?? 0;
    const skewValue = applySkew(newValue, 0.0, 1.0, 0.15);
    const y = height - skewValue * height;

    // smoothing
    const alpha = 0.2;
    smoothedYRef.current += alpha * (y - smoothedYRef.current);
    const smoothedY = smoothedYRef.current;

    // Canvas 업데이트
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
  });

  return <canvas ref={canvasRef} width={width} height={height} />;
}
