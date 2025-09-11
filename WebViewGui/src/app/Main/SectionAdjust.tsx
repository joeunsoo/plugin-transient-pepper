import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import Box from '@mui/material/Box';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      alignItems="end"
      justifyContent="center"
      spacing="var(--column-spacing)"
      sx={{
        ...sx
      }}
      {...props}
    >
      <JuceKnob
        identifier="thresholdSlider"
        defaultValue={0.5}
        subDigit={1}
      />
      <JuceKnob
        identifier="emphasisSlider"
        defaultValue={0.5}
        subDigit={1}
      />
      <Box sx={{ width: '3em' }} />
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
