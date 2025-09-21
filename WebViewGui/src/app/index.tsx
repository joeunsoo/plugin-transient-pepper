import { Box } from '@mantine/core';
import Stack from '@mui/material/Stack';
import Paper from '@mui/material/Paper';

import Main from './Main';
import Header from './Header';
import Provider from './Provider';
import { GlassSx } from '@/define';

export default function App() {
  return (
    <Provider>
      <Box
        style={{
          display: 'flex',
          minHeight: '100dvh',
          overflow: 'hidden',
          userSelect: 'none',
        }}
      >
        <Stack
          sx={{
            flexGrow: 1,
            px: 3,
            pt: 0,
            pb: 2,
          }}
        >
          <Header />
          <Stack
            alignItems="center"
            justifyContent="center"
            sx={{
              height: '100%',
            }}
          >
            <Paper
              sx={{
                width: '100%',
                height: '100%',
                display: 'flex',
                borderRadius: 5,
                background: `
                  linear-gradient(
                    to bottom,
                    rgba(255,255,255,0.1),
                    rgba(255,255,255,0) 100%
                  )
                `,
                ...GlassSx
              }}
            >
              <Main />
            </Paper>
          </Stack>
        </Stack>
      </Box>
    </Provider>
  );
}
