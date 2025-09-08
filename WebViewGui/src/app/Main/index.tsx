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
      <Grid size={12}>
        <Stack
          direction="row"
          alignItems="center"
          justifyContent="center"
          sx={{
            display:'grid',
            gridTemplateColumns: 'repeat(5, minmax(7em, auto))'
          }}
        >

          <JuceKnob
            identifier="transientAmountSlider"
            title="Attack"
            defaultValue={0.5}
            subDigit={4}
            sx={{
              flexShrink: 0
            }}
          />
          <JuceKnob
            identifier="emphasisSlider"
            title="Release"
            defaultValue={0.5}
            subDigit={4}
            sx={{
              flexShrink: 0
            }}
          />
          <JuceKnob
            identifier="tiltSlider"
            title="Threshold"
            defaultValue={0.5}
            subDigit={4}
          />
          <JuceKnob
            identifier="attackSlider"
            title="Attack2"
            defaultValue={0.5}
            subDigit={4}
            sx={{
              flexShrink: 0
            }}
          />
          <JuceKnob
            identifier="releaseSlider"
            title="Release2"
            defaultValue={0.5}
            subDigit={4}
          />
          <JuceKnob
            identifier="inputGainSlider"
            title="TAttack"
            defaultValue={0.5}
            subDigit={1}
          />
          <JuceKnob
            identifier="outputGainSlider"
            title="TRelease"
            defaultValue={0.5}
            subDigit={1}
          />
          <JuceKnob
            identifier="dryWetSlider"
            title="Threshold"
            defaultValue={1.0}
            subDigit={1}
          />
          <JuceKnob
            identifier="saturationDriveSlider"
            title="Noise Level"
            defaultValue={0.5}
            subDigit={1}
            sx={{
              flexShrink: 0
            }}
          />
          <Stack>
            <JuceToggleButton
              identifier="masterToggle"
              title="In"
            />
          </Stack>
        </Stack>
      </Grid>
    </Grid>
  );
}
