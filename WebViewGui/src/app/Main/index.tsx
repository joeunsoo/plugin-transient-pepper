import Stack from '@mui/material/Stack';

import SectionAdjust from './SectionAdjust';
import SectionShape from './SectionShape';
import SectionMix from './SectionMix';
import SectionNoiseGain from './SectionNoiseGain';
import { GlassSx, palette } from '@/define';
import { alpha } from '@mui/material/styles';

export default function App() {
  return (
    <Stack
      alignItems="center"
      justifyContent="center"
      sx={{
        py: 4,
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
        justifyContent="space-between"
        sx={{
          width: '100%',
          height: '100%',
          '> *': {
            height: '100%',
          },
          '--knob-width': '5.3em',
          '--row-spacing': '0.6em',
          '--column-spacing': '0.4em',
        }}
      >
        <Stack
          direction="row"
          justifyContent="space-between"
          spacing={4}
          sx={{
            flexGrow: 1,
            p: 4,
          }}
        >
          <Stack
            direction="column"
            sx={{
              width: '100%'
            }}
          >
            <SectionShape sx={{ flexGrow: 1 }} />
            <SectionAdjust />
          </Stack>
        </Stack>
        <Stack
          direction="row"
          sx={{
            flexShrink: 0,
            p: 4,
            borderRadius: 3,
            background: `
              linear-gradient(
                to bottom,
                ${alpha(palette.secondary.main, 0.3)},
                ${alpha(palette.secondary.main, 0)} 100%
              )
            `,
            outline: `1px solid ${alpha(palette.secondary.darker, 0.3)}`,
            ...GlassSx
          }}
        >
          <SectionNoiseGain />
        </Stack>
        <Stack
          direction="row"
          justifyContent="end"
          sx={{
            flexShrink: 0,
            p: 4,
          }}
        >
          <SectionMix />
        </Stack>
      </Stack>
    </Stack>
  );
}
