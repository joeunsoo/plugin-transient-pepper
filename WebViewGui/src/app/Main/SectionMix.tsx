import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import NoiseGain from './NoiseGain';
import OutputGain from './OutputGain';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      alignItems="center"
      justifyContent="end"
      spacing="var(--column-spacing)"
      sx={{
        '> *': {
          height: '100%',
        },
        ...sx
      }}
      {...props}
    >
      <Stack
        direction="column"
        alignItems="center"
        justifyContent="end"
        spacing="var(--row-spacing)"
      >
        <Stack
          direction="row"
          sx={{ flexGrow: 1 }}
        >
          <NoiseGain />
        </Stack>
        <JuceKnob
          identifier="dryWetSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
          ignoreWetSolo={false}
        />
      </Stack>

      <OutputGain />
    </Stack>
  );
}
