import Stack from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import { msToString } from '@/utils/valueToString';
import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

export default function App() {
  return (

    <Stack
      direction="row"
      alignItems="center"
      justifyContent="center"
      sx={{
        display: 'grid',
        gridTemplateColumns: '1fr 2fr',
        '> *': {
          height: '100%',
        }
      }}
    >

      <Stack
        alignItems="center"
        justifyContent="center"
        sx={{
          height:'100%'
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
        alignItems="center"
        justifyContent="center"
        sx={{
          width: '14em',
          flexWrap: 'wrap',
          height:'fit-content'
        }}
      >
        <JuceKnob
          identifier="releaseSlider"
          defaultValue={0.5}
          valueToString={msToString}
          subDigit={1}
        />
        <JuceKnob
          identifier="emphasisSlider"
          defaultValue={0.5}
          subDigit={1}
        />
        <JuceKnob
          identifier="attackSlider"
          defaultValue={0.5}
          valueToString={msToString}
          subDigit={1}
        />
      </Stack>
    </Stack>
  );
}
