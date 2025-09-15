'use client';

import { useState } from 'react';
import { useAnimationFrame } from 'framer-motion';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';

import Stack, { type StackProps } from '@mui/material/Stack';

import PeakMeterBar from '@/ui/Meter/PeakMeterBarCanvas';
import type { PeakMeterProps } from '@/types/PeakMeter';

export default function Page({
  idx,
  sx,
  ignoreBypass=false,
  ...props
}: PeakMeterProps & StackProps) {
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
        flexGrow: 1,
        width: '100%',
        maxWidth: '2.8em',
        ...sx
      }}
      {...props}
    >
      <PeakMeterBar
        idx={idx}
        ignoreBypass={ignoreBypass}
      />
      {numChannels > 1 &&
        <PeakMeterBar
          idx={idx + 1}
          ignoreBypass={ignoreBypass}
        />
      }
    </Stack>
  );
}
