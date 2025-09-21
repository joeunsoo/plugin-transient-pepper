import { useState } from 'react';

import { Group, Stack, type StackProps } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import SectionTitle from './SectionTitle';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import { uesControlStore } from '@/store/ControlStore';

export default function Page({
  sx, ...props
}: StackProps) {
  const [bpfOn, setBpfOn] = useState<boolean>(true);
  const { setThreshold } = uesControlStore();

  return (
    <Stack
      justify="space-between"
      gap="var(--row-spacing)"
      sx={{
        ...sx
      }}
      {...props}
    >
      <SectionTitle>
        Transient Detector
      </SectionTitle>
      <Group
        justify="start"
        gap="var(--column-spacing)"
      >
        <JuceToggleButton
          identifier="linkChannelsToggle"
          title="L/R Link"
        />
        <JuceToggleButton
          identifier="bpfPowerToggle"
          title="BPF On"
          onChange={(e, value) => setBpfOn(!value)}
        />
      </Group>

      <Group
        justify="start"
        gap="var(--column-spacing)"
      >
        <JuceKnob
          identifier="thresholdSlider"
          defaultValue={0.5}
          subDigit={1}
          ringColor="secondary"
          onChange={(v) => setThreshold(v)}
        />
        <JuceKnob
          identifier="bpfFrequencySlider"
          defaultValue={0.5}
          subDigit={1}
          addTest={[bpfOn]}
        />
      </Group>
    </Stack>
  );
}
