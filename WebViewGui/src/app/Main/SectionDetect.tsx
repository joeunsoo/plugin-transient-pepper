import Stack from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';

export default function App() {
  return (
    <Stack
      direction="row"
      alignItems="center"
      justifyContent="center"
      sx={{
        width: '14em',
        flexWrap: 'wrap-reverse',
      }}
    >
      <JuceToggleButton
        identifier="linkChannelsToggle"
        title="Link"
      />
      <JuceToggleButton
        identifier="linkChannelsToggle"
        title="Link"
      />
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
      <PeakMeterStereo idx={0} />
    </Stack>
  );
}
