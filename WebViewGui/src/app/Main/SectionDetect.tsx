import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import SectionTitle from './SectionTitle';
import Box from '@mui/material/Box';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      alignItems="center"
      alignContent="flex-start"
      justifyContent="space-between"
      spacing="var(--column-spacing)"
      sx={{
        flexWrap: 'wrap',
        ...sx
      }}
      {...props}
    >
      <SectionTitle sx={{ width: '100%' }}>
        Transient Noise Sculptor
      </SectionTitle>
      <JuceKnob
        identifier="thresholdSlider"
        defaultValue={0.5}
        subDigit={1}
        sx={{
          '--knob-width': '8.0em',
        }}
      />
      <Box sx={{ width: 'var(--knob-width)' }} />
      <Box sx={{ width: 'var(--knob-width)' }} />
    </Stack>
  );
}
