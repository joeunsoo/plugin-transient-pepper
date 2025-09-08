import * as Juce from 'juce-framework-frontend';

import Grid from '@mui/material/Grid';
import Stack from '@mui/material/Stack';

import JuceKnob from '@/src/ui/Control/Slider/JuceKnob';

import controlParameterIndexAnnotation from '@/src/define/controlParameterIndexAnnotation';
import JuceToggleButton from '@/src/ui/Control/ToggleButton/JuceToggleButton';

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
      <Grid size={6}>
        <Stack
          direction="row"
          alignItems="center"
          justifyContent="center"
          sx={{
            display: 'grid',
            gridTemplateColumns: '1fr 1fr',
            columnGap: 8,
            rowGap: 2,
          }}
        >
          <JuceKnob
            identifier="saturationDriveSlider"
            title="Drive"
            defaultValue={0.5}
            subDigit={1}
            sx={{
              flexShrink: 0
            }}
          />
          <JuceKnob
            identifier="emphasisSlider"
            title="Emphasis"
            defaultValue={0.5}
            subDigit={1}
            sx={{
              flexShrink: 0
            }}
          />
          <JuceKnob
            identifier="tiltSlider"
            title="Tone/Tilt"
            defaultValue={0.5}
            subDigit={1}
          />
        </Stack>
      </Grid>
      <Grid size={6}>
        <Stack
          direction="row"
          alignItems="center"
          justifyContent="center"
          sx={{
            display: 'grid',
            gridTemplateColumns: '1fr 1fr',
            columnGap: 8,
            rowGap: 2,
          }}
        >
          <JuceKnob
            identifier="inputGainSlider"
            title="Input"
            defaultValue={0.5}
            subDigit={1}
          />
          <JuceKnob
            identifier="outputGainSlider"
            title="Output"
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
              identifier="bypassToggle"
            />
          </Stack>
        </Stack>
      </Grid>
    </Grid>
  );
}
