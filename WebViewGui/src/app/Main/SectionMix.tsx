
import { useState } from 'react';
import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import NoiseGain from './NoiseGain';
import OutputGain from './OutputGain';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';

export default function Page({
  sx, ...props
}: StackProps) {
  const [wetSolo, setWetSolo] = useState<boolean>(false);

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
        <JuceToggleButton
          identifier="wetSoloToggle"
          title="Wet Solo"
          onChange={(e, value) => setWetSolo(value)}
        />
        <JuceKnob
          identifier="dryWetSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
          addTest={[wetSolo]}
        />
      </Stack>

      <OutputGain />
    </Stack>
  );
}
