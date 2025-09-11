import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import NoiseGain from './NoiseGain';
import OutputGain from './OutputGain';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import { uesControlStore } from '@/store/ControlStore';

export default function Page({
  sx, ...props
}: StackProps) {
  const { setWetSolo } = uesControlStore();

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
          title={<>Wet<br />Solo</>}
          onChange={(e, value) => setWetSolo(value)}
        />
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
