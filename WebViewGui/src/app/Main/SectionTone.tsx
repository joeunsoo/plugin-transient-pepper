import Stack from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

export default function App() {
  return (
    <Stack
      direction="row"
      alignItems="center"
      justifyContent="center"
      sx={{
        width: '14em',
        flexWrap: 'wrap-reverse',
        height: 'fit-content'
      }}
    >
      <JuceKnob
        identifier="tiltSlider"
        defaultValue={0.5}
        subDigit={1}
      />
      <JuceKnob
        identifier="midSideSlider"
        defaultValue={0.5}
        subDigit={1}
      />
      <JuceKnob
        identifier="noiseLevelGainSlider"
        defaultValue={0.5}
        subDigit={1}
      />
    </Stack>
  );
}
