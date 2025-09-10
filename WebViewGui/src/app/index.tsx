
import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';
import Paper from '@mui/material/Paper';

import Main from './Main';
import Header from './Header';
import Provider from './Provider';
import { noDragSx } from '@/define';

export default function App() {
  return (
    <Provider>
      <Box
        sx={{
          display: 'flex',
          minHeight: '100dvh',
          overflow: 'hidden',
          ...noDragSx
        }}
      >
        <Stack
          sx={{
            flexGrow: 1,
            px: 5,
            pt: 1,
            pb: 5,
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
                boxShadow: 'none',
                background: `
                  linear-gradient(
                    to bottom, rgba(255,255,255,0.6), rgba(255,255,255,0) 100%
                  )
                `
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
