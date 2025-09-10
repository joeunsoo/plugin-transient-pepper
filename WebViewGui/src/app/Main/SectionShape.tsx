import Stack from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';
import { msToString } from '@/utils/valueToString';

export default function App() {
  return (
    <Stack
      direction="row"
      alignItems="center"
      justifyContent="center"
      sx={{
        width:'14em',
        flexWrap: 'wrap',
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
        identifier="attackSlider"
        defaultValue={0.5}
        valueToString={msToString}
        subDigit={1}
      />
      <JuceKnob
        identifier="releaseSlider"
        defaultValue={0.5}
        valueToString={msToString}
        subDigit={1}
      />
    </Stack>
  );
}
