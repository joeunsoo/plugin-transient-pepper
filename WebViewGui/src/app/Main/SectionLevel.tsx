import Stack from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

export default function App() {
  return (
    <Stack
      direction="row"
      alignItems="center"
      justifyContent="end"
      spacing={2}
      sx={{
        '> *': {
          height: '100%',
        }
      }}
    >
      <Stack
        alignItems="center"
        justifyContent="end"
      >
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
            identifier="linkChannelsToggle"
            title="Link"
          />
          <JuceToggleButton
            identifier="wetSoloToggle"
          />
          <JuceToggleButton
            identifier="bypassToggle"
            title="In"
            invertValue
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
