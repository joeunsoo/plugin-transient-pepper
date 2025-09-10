import Stack from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

export default function App() {
  return (
    <Stack
      direction="row"
      alignItems="end"
      justifyContent="start"
      spacing={2}
    >
      <Stack
        alignItems="center"
        justifyContent="center"
        spacing={3}
        sx={{
          height: '100%',
        }}
      >
        <PeakMeterStereo idx={0} />
        <JuceKnob
          identifier="thresholdSlider"
          defaultValue={0.5}
          subDigit={1}
        />
      </Stack>
      <Stack
        direction="row"
        sx={{ flexShrink: 0 }}
      >
        <JuceKnob
          identifier="emphasisSlider"
          defaultValue={0.5}
          subDigit={1}
        />
      </Stack>
    </Stack>
  );
}
