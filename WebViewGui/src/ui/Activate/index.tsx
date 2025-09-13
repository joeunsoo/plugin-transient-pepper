'use client';

import {
  PluginName,
  GlassSx
} from '@/define';

import Paper from '@mui/material/Paper';
import Stack from '@mui/material/Stack';
import Modal from '@mui/material/Modal';

import { useActivateStore } from '@/store/ActivateStore';
import LoginForm from './LoginForm';
import Typography from '@mui/material/Typography';
import Deactivate from './Deactivate';

export default function App() {
  const { open, handleClose, activate } = useActivateStore();

  return (
    <Modal
      open={open}
      onClose={activate ? handleClose : undefined}
    >
      <Paper
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
          spacing={4}
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
          {!activate ? <LoginForm /> : <Deactivate />}
        </Stack>
      </Paper>
    </Modal>
  );
}
