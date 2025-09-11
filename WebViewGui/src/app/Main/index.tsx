import Stack from '@mui/material/Stack';

import SectionDetect from './SectionDetect';
import SectionShape from './SectionShape';
import SectionMix from './SectionMix';
import SectionNoiseGain from './SectionNoiseGain';
import Divider from '@mui/material/Divider';

export default function App() {
  return (
    <Stack
      alignItems="center"
      justifyContent="center"
      sx={{
        px: 5,
        py: 5,
        flexGrow: 1,
        '& .MuiGrid-root': {
          display: 'flex',
          flexDirection: 'column',
          alignItems: 'center',
          justifyContent: 'center',
        }
      }}
    >
      <Stack
        direction="row"
        alignItems="center"
        justifyContent="center"
        sx={{
          width: '100%',
          height: '100%',
          '> *': {
            flexGrow: 1,
            height: '100%',
          },
          '--knob-width': '5.0em',
          '--row-spacing': '0.6em',
          '--column-spacing': '0.4em',
        }}
      >
        <Stack
          direction="row"
          justifyContent="space-between"
          spacing={4}
          divider={
            <Divider
              orientation="vertical"
              sx={{
                width: 0,
                borderLeft: '1px solid #303030',
                borderRight: '1px solid var(--mui-palette-secondary-darker)',
                flexGrow: 0,
              }}
            />
          }
        >
          <Stack
            alignItems="stretch"
            justifyContent="stretch"
            sx={{
            px: 4,
            py: 4,
              '> *': {
                flexGrow: 1,
              },
            }}
          >
            <SectionDetect />
            <SectionShape />
          </Stack>
          <Stack
            direction="row"
            sx={{
              px: 4,
              py: 4,
              borderRadius: 3,
              backgroundColor: 'var(--mui-palette-secondary-darkermost)',
              outline: '1px solid var(--mui-palette-secondary-darker)',
              boxShadow: `
              0 1px 2px rgba(0,0,0,0.2),
              inset 0 1px 0 rgba(255,255,255,0.5)
            `,
            }}
          >
            <SectionNoiseGain />
          </Stack>
        </Stack>
        <Stack
          direction="row"
          sx={{
            pl: 4,
            py: 4
          }}
        >
          <SectionMix />
        </Stack>
      </Stack>
    </Stack>
  );
}
