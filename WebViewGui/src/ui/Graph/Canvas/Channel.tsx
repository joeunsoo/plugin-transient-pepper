import { useAnalysisDataStore } from '@/store/AnalysisDataStore';
import Draw, { type EnvelopeGraphProps } from './Draw';
import { useAnimationFrame, useMotionValue, useTransform } from 'framer-motion';
import applySkew from '@/utils/applySkew';
import { useRef } from 'react';

interface PageProps
  extends Omit<EnvelopeGraphProps, 'getValue' | 'canvasRef'> {
  idx: number
}
export default function EnvelopeGraph({
  idx,
  ...props
}: PageProps) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const { motionValues } = useAnalysisDataStore();

  const value = useMotionValue(0);
  const skewValue = useTransform(value, (value) => applySkew(value, 0.0, 1.0, 0.15));

  useAnimationFrame(() => {
    const newValue = (motionValues[idx].get() + motionValues[idx + 1].get()) / 2;
    value.set(newValue);
  });

  return (
    <>
      <Draw
        {...props}
        canvasRef={canvasRef}
        getValue={() => skewValue.get()}
      />
      <canvas ref={canvasRef} width={props.width} height={props.height} />
    </>
  );
}
