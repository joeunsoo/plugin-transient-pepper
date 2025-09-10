import * as Juce from 'juce-framework-frontend';

import Grid from '@mui/material/Grid';
import Stack from '@mui/material/Stack';

import JuceKnob from '@/ui/Control/Slider/JuceKnob';

import { controlParameterIndexAnnotation } from '@/define';
import JuceToggleButton from '@/ui/Control/ToggleButton/JuceToggleButton';
import { msToString } from '@/utils/valueToString';
import PeakMeterStereo from '@/ui/Meter/PeakMeterStereo';

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
            gridTemplateColumns: '2fr 1fr 2fr 1fr'
          }}
        >
          <Stack
            direction="row"
            alignItems="center"
            justifyContent="center"
            sx={{
              display: 'grid',
              gridTemplateColumns: 'repeat(2, 1fr)'
            }}
          >
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
          <Stack
            direction="row"
            alignItems="center"
            justifyContent="center"
            sx={{
              display: 'grid',
              gridTemplateColumns: 'repeat(1, 1fr)'
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
          </Stack>

          <Stack
            direction="row"
            alignItems="center"
            justifyContent="center"
            sx={{
              display: 'grid',
              gridTemplateColumns: 'repeat(2, 1fr)'
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
            />
            <JuceKnob
              identifier="dryWetSlider"
              title="Dry/Wet"
              defaultValue={0.5}
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
                title="Link"
              />
            </Stack>
          </Stack>

          <PeakMeterStereo id={0} />
        </Stack>
      </Grid>
    </Grid>
  );
}
