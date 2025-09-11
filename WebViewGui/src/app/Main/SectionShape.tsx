import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import { msToString } from '@/utils/valueToString';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      alignItems="center"
      alignContent="flex-end"
      justifyContent="space-between"
      spacing="var(--column-spacing)"
      sx={{
        flexWrap: 'wrap',
        ...sx
      }}
      {...props}
    >
      <JuceKnob
        identifier="emphasisSlider"
        defaultValue={0.5}
        subDigit={1}
      />
      <JuceKnob
        identifier="attackSlider"
        defaultValue={0.5}
        valueToString={msToString}
        subDigit={1}
      />
      <JuceKnob
        identifier="releaseSlider"
        defaultValue={0.5}
        valueToString={msToString}
        subDigit={1}
      />
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
