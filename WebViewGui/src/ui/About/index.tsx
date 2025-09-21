'use client';

import {
  PluginName,
  CompanyName,
  PluginVersion,
  GlassSx,
  mantineSpace
} from '@/define';

import Modal from '@mui/material/Modal';

import { useAboutStore } from '@/store/AboutStore';
import { Paper, rem, Stack, Text, Title } from '@mantine/core';

export default function App() {
  const { open, handleClose } = useAboutStore();

  return (
    <Modal
      open={open}
      onClose={handleClose}
    >
      <Paper
        onClick={handleClose}
        p={rem(mantineSpace * 4)}
        bg="primary.8"
        sx={{
          position: 'absolute',
          top: '50%',
          left: '50%',
          width: '50%',
          boxSizing: 'border-box',
          transform: 'translate(-50%, -50%)',
          ...GlassSx,
        }}
      >
        <Stack align="center">
          <Title order={4}>
            {PluginName}
          </Title>
          <Text size="sm">
            {PluginVersion}
          </Text>
          <Title order={6} pt={rem(mantineSpace * 4)}>
            &copy; {CompanyName}.
          </Title>
        </Stack>
      </Paper>
    </Modal>
  );
}
