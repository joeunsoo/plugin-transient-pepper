'use client';

import { useState } from 'react';
import { useAnimationFrame } from 'framer-motion';
import { useAnalysisDataStore } from '@/store/AnalysisDataStore';

import { Group, rem, type GroupProps } from '@mantine/core';

import PeakMeterBarCanvas from '@/ui/Meter/PeakMeterBarCanvas';
import type { PeakMeterProps } from '@/types/PeakMeter';
import { mantineSpace } from '@/define';

export default function Page({
  idx,
  style,
  ignoreBypass=false,
  ...props
}: PeakMeterProps & GroupProps) {
  const { outputNumChannels } = useAnalysisDataStore();
  const [numChannels, setNumChannels] = useState<number>(0);

  useAnimationFrame(() => {
    setNumChannels(outputNumChannels.get());
  });

  return (
    <Group
      align="center"
      gap={rem(mantineSpace * 1.5)}
      style={{
        flexGrow: 1,
        width: '100%',
        maxWidth: '2.8em',
        ...style
      }}
      {...props}
    >
      <PeakMeterBarCanvas
        idx={idx}
        ignoreBypass={ignoreBypass}
      />
      {numChannels > 1 &&
        <PeakMeterBarCanvas
          idx={idx + 1}
          ignoreBypass={ignoreBypass}
        />
      }
    </Group>
  );
}
