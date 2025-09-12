'use client';

import {
  PluginName,
  CompanyName,
  PluginVersion,
  GlassSx
} from '@/define';

import Paper from '@mui/material/Paper';
import Stack from '@mui/material/Stack';
import Typography from '@mui/material/Typography';
import Modal from '@mui/material/Modal';

import { useAboutStore } from '@/store/AboutStore';

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
          ...GlassSx,
          p: 4
        }}
      >
        <Stack
          direction="column"
          alignItems="center"
          sx={{
            textAlign: 'center'
          }}
        >
          <Typography
            variant="h6"
            component="h2"
            sx={{
              fontWeight: 'var(--mui-fontWeight-xl)'
            }}
          >
            {PluginName}
          </Typography>
          <Typography
            variant="body2"
          >
            {PluginVersion}
          </Typography>
          <Typography
            sx={{
              pt:5,
              fontWeight: 'var(--mui-fontWeight-xl)'
            }}
          >
            &copy; {CompanyName}.
          </Typography>
        </Stack>
      </Paper>
    </Modal>
  );
}
