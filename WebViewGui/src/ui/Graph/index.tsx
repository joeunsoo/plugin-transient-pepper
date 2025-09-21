'use client';

import { palette } from '@/define';
import Path from './Path';
import Threshold from './Threshold';
import { alpha } from '@mantine/core';

export default function Page({
  ...props
}: React.SVGProps<SVGSVGElement>) {
  const pathProps = {
    maxPoints: 150,
    width: 383,
    height: 293
  };

  return (
    <svg viewBox="0 0 383 293" {...props}>
      <Path
        idx={4}
        fill={palette.primary.darkest}
        stroke={palette.primary.light}
        strokeWidth={2}
        {...pathProps}
      />
      <Path
        idx={6}
        fill={alpha(palette.secondary.dark, 0.3)}
        stroke={palette.secondary.main}
        strokeWidth={2}
        {...pathProps}
      />
      <Threshold
        stroke={palette.primary.main}
        strokeWidth={2}
        {...pathProps}
      />
    </svg>
  );
}
