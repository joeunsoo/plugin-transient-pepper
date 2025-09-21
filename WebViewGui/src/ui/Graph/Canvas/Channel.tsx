import { useEffect, useRef } from 'react';
import { useAnimationFrame } from 'framer-motion';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import applySkew from '@/utils/applySkew';

interface EnvelopeGraphProps {
  idx: number;
  width?: number;
  height?: number;
  stroke: string;
  fill?: string; // 밑부분 색
  scrollSpeed?: number; // 픽셀 이동 속도
}

export default function EnvelopeGraph({
  idx,
  width = 383,
  height = 293,
  stroke,
  fill = 'null', // 기본 반투명
  scrollSpeed = 1,
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

      if (!ctxRef.current) {
        return;
      }
      ctxRef.current.lineWidth = 2;
      ctxRef.current.strokeStyle = stroke;

      bufferRef.current = document.createElement('canvas');
      bufferRef.current.width = width;
      bufferRef.current.height = height;
    }
  }, [height, stroke, width]);

  useAnimationFrame((_time, delta) => {
    const canvas = canvasRef.current;
    const ctx = ctxRef.current;
    const buffer = bufferRef.current;
    if (!canvas || !ctx || !buffer) {
      return;
    }

    const bufCtx = buffer.getContext('2d')!;

    const newValue = (motionValues[idx].get() + motionValues[idx + 1].get()) / 2;
    const skewValue = applySkew(newValue, 0.0, 1.0, 0.15);

    const value = skewValue;
    const y = height - value * height;

    // 🟢 smoothing 적용 (alpha: 0~1, 작을수록 부드러움)
    const alpha = 0.2;
    smoothedYRef.current += alpha * (y - smoothedYRef.current);
    const smoothedY = smoothedYRef.current;

    // 1) 기존 그림을 왼쪽으로 scrollSpeed만큼 이동
    const movePixels = Math.floor(scrollSpeed * (delta / 10));

    // 1) 버퍼에 기존 그림 복사
    bufCtx.clearRect(0, 0, width, height);
    bufCtx.drawImage(canvasRef.current!, 0, 0, width, height, 0, 0, width, height);

    // 2) 캔버스를 왼쪽으로 이동
    ctx.clearRect(0, 0, width, height);
    ctx.drawImage(
      buffer,
      movePixels,
      0,
      width - movePixels,
      height,
      0,
      0,
      width - movePixels,
      height
    );

    // 3) 오른쪽 끝 영역 지우기
    ctx.clearRect(width - movePixels, 0, movePixels, height);

    // 3) 선 아래 영역 채우기
    ctx.beginPath();
    ctx.moveTo(width - movePixels - 1, lastYRef.current);

    const cpX = width - movePixels - 0.5;
    const cpY = (lastYRef.current + smoothedY) / 2;

    ctx.quadraticCurveTo(cpX, cpY, width - 1, smoothedY);

    // 바닥까지 연결 후 경로 닫기
    ctx.lineTo(width - 1, height);
    ctx.lineTo(width - movePixels - 1, height);
    ctx.closePath();

    if (fill) {
      ctx.fillStyle = fill;
      ctx.fill();
    }

    // 4) 선 그리기
    ctx.beginPath();
    ctx.moveTo(width - movePixels - 1, lastYRef.current);
    ctx.quadraticCurveTo(cpX, cpY, width - 1, smoothedY);
    ctx.stroke();

    lastYRef.current = smoothedY;
  });

  return <canvas ref={canvasRef} width={width} height={height} />;
}
