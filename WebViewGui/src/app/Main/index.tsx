import * as Juce from 'juce-framework-frontend';

import Grid from '@mui/material/Grid';
import Stack from '@mui/material/Stack';

import JuceKnob from '@/src/ui/Control/Slider/JuceKnob';

import controlParameterIndexAnnotation from '@/src/define/controlParameterIndexAnnotation';
import JuceToggleButton from '@/src/ui/Control/ToggleButton/JuceToggleButton';
import { msToString } from '@/src/utils/valueToString';

export default function App() {
  const controlParameterIndexUpdater = new Juce.ControlParameterIndexUpdater(
    controlParameterIndexAnnotation
  );

  document.addEventListener('mousemove', (event) => {
    controlParameterIndexUpdater.handleMouseMove(event);
  });

  return (
    <Grid
      container
      sx={{
        flexGrow: 1,
        '--Grid-borderWidth': '1px',
        '& > div': {
          borderRight: 'var(--Grid-borderWidth) solid',
          borderColor: 'divider',
        },
        '& > div:last-child': {
          borderRight: 'none',
        },
        '& .MuiGrid-root': {
          display: 'flex',
          flexDirection: 'column',
          alignItems: 'center',
          justifyContent: 'center',
        }
      }}
    >
      <Grid size={12}>
        <Stack
          direction="row"
          alignItems="center"
          justifyContent="center"
          sx={{
            display: 'grid',
            gridTemplateColumns: 'repeat(5, minmax(7em, auto))'
          }}
        >

          <JuceKnob
            identifier="thresholdSlider"
            defaultValue={0.5}
            subDigit={4}
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
            identifier="emphasisSlider"
            defaultValue={0.5}
            subDigit={1}
          />
          <JuceKnob
            identifier="inputGainSlider"
            title="Input Gain"
            defaultValue={0.5}
            subDigit={1}
          />
          <JuceKnob
            identifier="outputGainSlider"
            title="Output Gain"
            defaultValue={0.5}
            subDigit={1}
          />
          <JuceKnob
            identifier="dryWetSlider"
            title="Dry/Wet"
            defaultValue={1.0}
            subDigit={1}
          />
          <Stack>
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
            />
          </Stack>
        </Stack>
      </Grid>
    </Grid>
  );
}
