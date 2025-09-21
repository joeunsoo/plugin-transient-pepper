'use client';

import { Modal, rem, Stack, Title } from '@mantine/core';
import { GlassSx, mantineSpace, PluginName } from '@/define';
import { useActivateStore } from '@/store/ActivateStore';
import Deactivate from './Deactivate';
import LoginForm from './LoginForm';

export default function App() {
  const { opened, close, activate } = useActivateStore();

  return (
    <Modal
      opened={opened}
      centered
      withCloseButton={false}
      onClose={() => {
        if (activate) close();
      }}
      p={rem(mantineSpace * 4)}
      styles={{
        content: {
          ...GlassSx,
        },
      }}
    >
      <Stack
        align="center"
        gap={rem(mantineSpace * 4)}
        sx={{
          textAlign: 'center',
        }}
      >
        <Title order={3} component="h2">
          {PluginName}
        </Title>
        {!activate ? <LoginForm /> : <Deactivate />}
      </Stack>
    </Modal>
  );
}
