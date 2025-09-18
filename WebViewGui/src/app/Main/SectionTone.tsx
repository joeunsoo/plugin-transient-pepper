import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

export default function Page({
  ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      justifyContent="flex-end"
      spacing="var(--column-spacing)"
      {...props}
    >
      <JuceKnob
        identifier="tiltSlider"
        defaultValue={0.5}
        subDigit={1}
      />
      <JuceKnob
        identifier="midSideSlider"
        defaultValue={0.5}
        subDigit={1}
      />
    </Stack>
  );
}
