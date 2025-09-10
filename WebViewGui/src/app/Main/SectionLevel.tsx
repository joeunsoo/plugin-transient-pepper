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
        gridTemplateColumns: '1fr 1fr',
        '> *': {
          height: '100%',
        }
      }}
    >
      <Stack
        direction="row"
        alignItems="center"
        justifyContent="center"
        sx={{
          width: '14em',
          flexWrap: 'wrap-reverse'
        }}
      >
        <JuceKnob
          identifier="noiseLevelGainSlider"
          defaultValue={0.5}
          subDigit={1}
        />
        <JuceKnob
          identifier="outputGainSlider"
          defaultValue={0.5}
          subDigit={1}
          sx={{
            flexShrink: 0
          }}
        />
        <PeakMeterStereo idx={0} />
      </Stack>

      <Stack
        direction="column"
        alignItems="center"
        justifyContent="end"
      >
        <Stack
          sx={{
            flexShrink: 0,
          }}
        >
          <JuceToggleButton
            identifier="wetSoloToggle"
          />
          <JuceToggleButton
            identifier="bypassToggle"
            title="In"
            invertValue
          />
          <JuceToggleButton
            identifier="linkChannelsToggle"
            title="Link"
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
