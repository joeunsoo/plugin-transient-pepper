'use client';

import { motion, useAnimationFrame, useMotionValue, useTransform, type SVGMotionProps } from 'framer-motion';

import applySkew from '@/utils/applySkew';
import { uesControlStore } from '@/store/ControlStore';

interface PageProps extends SVGMotionProps<SVGLineElement> {
  width: number,
  height: number,
}

export default function Page({
  width,
  height,
  ...props
}: PageProps) {
  const { threshold } = uesControlStore();

  const value = useMotionValue(0);
  const reverse = useTransform(value, [0.0, 1.0], [1.0, 0.0]);
  const skewValue = useTransform(reverse, (value) => applySkew(value, 0.0, 1.0, 0.15));
  const scaleValue = useTransform(skewValue, [0.0, 1.0], [0, height]);

  useAnimationFrame(() => {
    value.set(threshold);
  });

  return (
    <motion.line
      r={height}
      x1={0}
      y1={scaleValue}
      x2={width}
      y2={scaleValue}
      transition={{ duration: 0, ease: 'linear' }}
      {...props}
    />
  );
}
