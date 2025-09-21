'use client';

import {
  PluginName,
  CompanyName,
  PluginVersion,
  GlassSx,
  mantineSpace
} from '@/define';

import { useAboutStore } from '@/store/AboutStore';
import { Modal, rem, Stack, Text, Title } from '@mantine/core';

export default function App() {
  const { opened, close } = useAboutStore();

  return (
    <Modal
      opened={opened}
      onClose={close}
      centered
      withCloseButton={false}
      p={rem(mantineSpace * 4)}
      styles={{
        content: {
          ...GlassSx,
        }
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
    </Modal>
  );
}
