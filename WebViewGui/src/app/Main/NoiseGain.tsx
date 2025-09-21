import { Stack, type StackProps } from '@mantine/core';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

export default function Page({
  ...props
}: StackProps) {
  return (
    <Stack
      align="center"
      justify="end"
      gap="var(--row-spacing)"
      {...props}
    >
      <PeakMeterStereo idx={6} />
      <JuceKnob
        identifier="noiseLevelGainSlider"
        defaultValue={0.5}
        subDigit={1}
        ringColor="secondary"
      />
    </Stack>
  );
}
