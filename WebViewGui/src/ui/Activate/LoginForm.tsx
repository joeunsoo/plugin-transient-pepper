'use client';

import { useState } from 'react';
import { EnvelopeSimpleIcon, LockSimpleIcon } from '@phosphor-icons/react';
import * as Juce from 'juce-framework-frontend';
import { Controller, useForm } from 'react-hook-form';
import { Button, rem, Stack, Text, TextInput } from '@mantine/core';
import { CompanyWebsite, mantineSpace, PluginCode } from '@/define';
import { useActivateStore } from '@/store/ActivateStore';
import { useSnackbarStore } from '@/store/SnackbarStore';
import Trial from './Trial';

type LoginFormValues = {
  userEmail: string;
  userPassword: string;
};

const visitWebsite = Juce.getNativeFunction('visitWebsite');
const setActivateJuce = Juce.getNativeFunction('setActivate');

export default function LoginForm() {
  const { setActivate, close } = useActivateStore();
  const { enqueueSnackbar } = useSnackbarStore();
  const [loading, setLoading] = useState<boolean>(false);

  // 2. RHF useForm 설정
  const {
    handleSubmit,
    control,
    formState: { isSubmitting },
  } = useForm<LoginFormValues>({
    defaultValues: { userEmail: '', userPassword: '' },
  });

  // 3. 폼 제출
  const onSubmit = async (values: LoginFormValues) => {
    if (!values.userEmail) {
      enqueueSnackbar('Email is required.', { variant: 'error' });

      return;
    }

    if (!values.userPassword) {
      enqueueSnackbar('Password is required.', { variant: 'error' });

      return;
    }

    try {
      setLoading(true);
      const res = await fetch(`${CompanyWebsite}/api/productActivation`, {
        method: 'POST',
        body: JSON.stringify({
          userEmail: values.userEmail,
          userPassword: values.userPassword,
          productCode: PluginCode,
        }),
        cache: 'no-store',
      })
        .then((res) => res.json().then((data) => ({ ok: res.ok, status: res.status, body: data })))
        .catch((err) => {
          // 서버 에러
          // eslint-disable-next-line no-console
          console.error(err);
          enqueueSnackbar('Unexpected error occurred', { variant: 'error' });
        });
      if (res?.ok) {
        setActivateJuce(values.userEmail);
        setActivate(true);
        close();
        enqueueSnackbar('Activate successful', { variant: 'success' });
      } else {
        enqueueSnackbar(res?.body.message, { variant: 'error' });
      }
      setLoading(false);
    } catch (err) {
      // eslint-disable-next-line no-console
      console.error(err);
      enqueueSnackbar('Unexpected error occurred', { variant: 'error' });
    }
  };

  return (
    <form onSubmit={handleSubmit(onSubmit)}>
      <Stack gap={rem(mantineSpace * 3)}>
        <Controller
          name="userEmail"
          control={control}
          render={({ field }) => (
            <TextInput
              {...field}
              label="Email"
              ta="left"
              leftSection={<EnvelopeSimpleIcon size="1.0em" weight="bold" />}
            />
          )}
        />

        <Controller
          name="userPassword"
          control={control}
          render={({ field }) => (
            <TextInput
              {...field}
              type="password"
              label="Password"
              ta="left"
              leftSection={<LockSimpleIcon size="1.0em" weight="bold" />}
            />
          )}
        />

        <Stack align="end">
          <Text
            ta="right"
            onClick={() => {
              visitWebsite(`${CompanyWebsite}/reset-password`);
            }}
            sx={{
              fontSize: 'var(--mantine-font-size-xs)',
            }}
          >
            Forgot password?
          </Text>
        </Stack>
        <Button loading={loading} type="submit" variant="contained" disabled={isSubmitting}>
          Sign in
        </Button>

        <Trial />
      </Stack>
    </form>
  );
}
