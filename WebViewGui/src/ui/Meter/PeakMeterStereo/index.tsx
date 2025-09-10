'use client';

import { useState } from 'react';
import { useAnimationFrame } from 'framer-motion';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';

import Stack from '@mui/material/Stack';

import PeakMeter from '../PeakMeter';

type PageProps = {
  id: number,
  length?: number
}

export default function Page({
  id,
  length
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
      spacing={2}
      sx={{
        width: 'fit-content',
        mx: 'auto'
      }}
    >
      {numChannels > 0 &&
        <PeakMeter id={id} length={length} />
      }
      {numChannels > 1 &&
        <PeakMeter id={id + 1} length={length} />
      }
    </Stack>
  );
}
