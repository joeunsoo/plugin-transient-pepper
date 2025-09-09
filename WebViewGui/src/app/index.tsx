
import Box from '@mui/material/Box';
import Stack from '@mui/material/Stack';
import Paper from '@mui/material/Paper';

import Main from './Main';
import Header from './Header';
import Provider from './Provider';

export default function App() {
  return (
    <Provider>
      <Box
        sx={{
          display: 'flex',
          minHeight: '100dvh',
          overflow: 'hidden',
        }}
      >
        <Stack
          sx={{
            flexGrow: 1,
            px: 5,
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
