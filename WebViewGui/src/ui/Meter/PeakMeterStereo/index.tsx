'use client';

import { useState } from 'react';
import { useAnimationFrame } from 'framer-motion';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';

import Stack, { type StackProps } from '@mui/material/Stack';

import PeakMeter from '../PeakMeter';

interface PageProps extends StackProps {
  idx: number,
  length?: number
}

export default function Page({
  idx,
  length,
  sx,
  ...props
}: PageProps) {
  const { outputNumChannels } = useAnalysisDataStore();
  const [numChannels, setNumChannels] = useState<number>(0);

  useAnimationFrame(() => {
    setNumChannels(outputNumChannels.get());
  });

  return (
    <Stack
      direction="row"
      alignItems="center"
      spacing={1.5}
      sx={{
        width:'100%',
        maxWidth:'4em',
        height:'100%',
        flexGrow:1,
        ...sx
      }}
      {...props}
    >
      {numChannels > 0 &&
        <PeakMeter idx={idx} length={length} />
      }
      {numChannels > 1 &&
        <PeakMeter idx={idx + 1} length={length} />
      }
    </Stack>
  );
}
