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
        position: 'relative',
        pb:'8.5em',
      }}
    >
      <Stack
        direction="row"
        alignItems="center"
        justifyContent="center"
        spacing={2}
        sx={{
          position: 'absolute',
          backgroundColor: 'var(--mui-palette-info-darker)',
          border: '0.2em solid var(--mui-palette-info-darkest)',
          width:'30em',
          height:'15.5em',
          borderRadius: 3,
        }}
      >
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
      </Stack>
    </Stack>
  );
}
