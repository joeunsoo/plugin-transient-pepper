'use client';

import { motion, useAnimationFrame, type SVGMotionProps } from 'framer-motion';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';

import applySkew from '@/utils/applySkew';
import { useState } from 'react';
import generatePathData from '@/utils/generatePathData';

interface PageProps extends SVGMotionProps<SVGPathElement> {
  idx:number,
  maxPoints: number,
  width: number,
  height: number,
}

export default function Page({
  idx,
  maxPoints,
  width,
  height,
  ...props
}: PageProps) {
  const { motionValues } = useAnalysisDataStore();
  const [values, setValues] = useState<number[]>(Array.from({ length: maxPoints }, () => 0));
  const [pathData, setPathData] = useState<string>('M0,50');

  useAnimationFrame(() => {
    const newValue = (motionValues[idx].get() + motionValues[idx + 1].get()) / 2;
    const skewValue = applySkew(newValue, 0.0, 1.0, 0.15);
    const { newValues, pathData } = generatePathData(
      values,
      skewValue,
      maxPoints,
      width,
      height
    );
    setValues(newValues);
    setPathData(pathData);
  });

  return (
    <motion.path
      d={pathData}
      r={height}
      fill="none"
      animate={{ d: pathData }}
      transition={{ duration: 0, ease: 'linear' }}
      {...props}
    />
  );
}
