import { useEffect, useRef } from 'react';

export type EnvelopeGraphProps = {
  width?: number;
  height?: number;
  getValue: () => number; // 0.0 ~ 1.0
  canvasRef: React.RefObject<HTMLCanvasElement | null>;
  stroke: string;
  fill?: string;       // 밑부분 색
  scrollSpeed?: number; // 픽셀 이동 속도
};

export default function EnvelopeGraph({
  width = 383,
  height = 293,
  getValue,
  canvasRef,
  stroke,
  fill = 'null', // 기본 반투명
  scrollSpeed = 1
}: EnvelopeGraphProps) {
  const lastYRef = useRef(height);
  const smoothedYRef = useRef(height); // smoothed value

  useEffect(() => {
    const canvas = canvasRef.current!;
    const ctx = canvas.getContext('2d')!;

    ctx.lineWidth = 2;
    ctx.strokeStyle = stroke;

    function draw() {
      const value = getValue();
      const y = height - value * height;

      // 🟢 smoothing 적용 (alpha: 0~1, 작을수록 부드러움)
      const alpha = 0.2;
      smoothedYRef.current = smoothedYRef.current + alpha * (y - smoothedYRef.current);
      const smoothedY = smoothedYRef.current;

      // 1) 기존 그림을 왼쪽으로 scrollSpeed만큼 이동
      const movePixels = Math.floor(scrollSpeed);
      const imageData = ctx.getImageData(movePixels, 0, width - movePixels, height);
      ctx.putImageData(imageData, 0, 0);

      // 2) 오른쪽 끝 영역 지우기
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

      ctx.fillStyle = fill;
      ctx.fill();

      // 4) 선 그리기
      ctx.beginPath();
      ctx.moveTo(width - movePixels - 1, lastYRef.current);
      ctx.quadraticCurveTo(cpX, cpY, width - 1, smoothedY);
      ctx.stroke();

      lastYRef.current = smoothedY;

      requestAnimationFrame(draw);
    }

    draw();
  }, [width, height, getValue, canvasRef, stroke, fill, scrollSpeed]);

  return null;
}
