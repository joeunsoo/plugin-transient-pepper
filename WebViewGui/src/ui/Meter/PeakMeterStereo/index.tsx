'use client';

import { useState } from 'react';
import { useAnimationFrame } from 'framer-motion';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';

import Stack, { type StackProps } from '@mui/material/Stack';

import PeakMeter from '../PeakMeter';

interface PageProps extends StackProps {
  idx: number,
  length?: number
  ignoreBypass?:boolean
  ignoreWetSolo?:boolean
}

export default function Page({
  idx,
  length,
  sx,
  ignoreBypass=false,
  ignoreWetSolo=true,
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
        flexGrow: 1,
        width: '100%',
        maxWidth: '2.8em',
        ...sx
      }}
      {...props}
    >
      <PeakMeter
        idx={idx}
        length={length}
        ignoreBypass={ignoreBypass}
        ignoreWetSolo={ignoreWetSolo}
      />
      {numChannels > 1 &&
        <PeakMeter
          idx={idx + 1}
          length={length}
          ignoreBypass={ignoreBypass}
          ignoreWetSolo={ignoreWetSolo}
        />
      }
    </Stack>
  );
}
