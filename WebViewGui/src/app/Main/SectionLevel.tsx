import Stack, { type StackProps } from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

export default function Page({
  sx, ...props
}: StackProps) {
  return (
    <Stack
      direction="row"
      alignItems="center"
      justifyContent="end"
      spacing={2}
      sx={{
        pt: 1,
        pb: 4,
        '> *': {
          height: '100%',
        },
        ...sx
      }}
      {...props}
    >
      <Stack
        alignItems="center"
        justifyContent="end"
        spacing={3}
      >
        <PeakMeterStereo idx={2} />
        <JuceKnob
          identifier="noiseLevelGainSlider"
          defaultValue={0.5}
          subDigit={1}
        />
      </Stack>

      <Stack
        direction="column"
        alignItems="center"
        justifyContent="end"
        spacing={3}
      >
        <PeakMeterStereo
          idx={0}
        />
        <JuceKnob
          identifier="outputGainSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
        />
      </Stack>
      <Stack
        direction="column"
        alignItems="center"
        justifyContent="end"
        spacing={1}
      >
        <Stack>
          <JuceToggleButton
            identifier="bypassToggle"
            title="In"
            invertValue
          />
          <JuceToggleButton
            identifier="linkChannelsToggle"
            title="L/R Link"
          />
          <JuceToggleButton
            identifier="wetSoloToggle"
          />
        </Stack>

        <JuceKnob
          identifier="dryWetSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
        />
      </Stack>
    </Stack>
  );
}
