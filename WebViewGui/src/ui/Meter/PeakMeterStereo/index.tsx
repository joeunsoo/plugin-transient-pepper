'use client';

import { Group, rem, type GroupProps } from '@mantine/core';

import PeakMeterBarCanvas from '@/ui/Meter/PeakMeterBarCanvas';
import type { PeakMeterProps } from '@/types/PeakMeter';
import { mantineSpace } from '@/define';
import { usePluginStore } from '@/store/PluginStore';

export default function Page({
  idx,
  style,
  ignoreBypass=false,
  ...props
}: PeakMeterProps & GroupProps) {
  const { numChannels } = usePluginStore();

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
