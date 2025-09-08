'use client';

import {
  PluginName,
  CompanyName,
  PluginVersion
} from '@/src/define';

import Paper from '@mui/material/Paper';
import Stack from '@mui/material/Stack';
import Typography from '@mui/material/Typography';
import Modal from '@mui/material/Modal';

import { useAboutStore } from '@/src/store/AboutStore';

export default function App() {
  const { open, handleClose } = useAboutStore();

  return (
    <Modal
      open={open}
      onClose={handleClose}
    >
      <Paper
        onClick={handleClose}
        sx={{
          position: 'absolute',
          top: '50%',
          left: '50%',
          width: '50%',
          boxSizing: 'border-box',
          transform: 'translate(-50%, -50%)',
          p: 4
        }}
      >
        <Stack
          direction="column"
          alignItems="center"
          spacing={0}
          sx={{
            textAlign: 'center'
          }}
        >
          <Typography variant="h6" component="h2">
            {PluginName}
          </Typography>
          <Typography>
            {PluginVersion}
          </Typography>
          <Typography>
            &copy; {CompanyName}.
          </Typography>
        </Stack>
      </Paper>
    </Modal>
  );
}
