import Stack from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

export default function App() {
  return (
    <Stack
      direction="row"
      alignItems="center"
      sx={{
        display: 'grid',
        gridTemplateColumns: '1fr 1fr 1fr',
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
        <JuceToggleButton
          identifier="bypassToggle"
          title="In"
          invertValue
        />
      </Stack>

      <Stack
        direction="column"
        alignItems="center"
        justifyContent="end"
      >

        <JuceKnob
          identifier="dryWetSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
        />
          <JuceToggleButton
            identifier="wetSoloToggle"
          />
      </Stack>

      <Stack
        direction="column"
        alignItems="center"
        justifyContent="end"
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
        <JuceToggleButton
          identifier="bypassToggle"
          title="In"
          invertValue
        />
      </Stack>

    </Stack>
  );
}
