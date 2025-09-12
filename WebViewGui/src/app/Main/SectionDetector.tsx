import { useState } from 'react';

import Stack, { type StackProps } from '@mui/material/Stack';

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
      direction="column"
      justifyContent="space-between"
      spacing="var(--row-spacing)"
      sx={{
        ...sx
      }}
      {...props}
    >
      <SectionTitle>
        Transient Detector
      </SectionTitle>
      <Stack
        direction="row"
        justifyContent="start"
        spacing="var(--column-spacing)"
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
      </Stack>

      <Stack
        direction="row"
        justifyContent="start"
        spacing="var(--column-spacing)"
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
      </Stack>
    </Stack>
  );
}
