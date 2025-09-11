import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

export default function Page({
  ...props
}: StackProps) {
  return (
    <Stack
      alignItems="center"
      justifyContent="end"
      spacing="var(--row-spacing)"
      {...props}
    >
      <PeakMeterStereo idx={2} />
      <JuceKnob
        identifier="noiseLevelGainSlider"
        defaultValue={0.5}
        subDigit={1}
      />
    </Stack>
  );
}
