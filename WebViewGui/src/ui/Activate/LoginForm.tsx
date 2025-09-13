'use client';

import { useSnackbarStore } from '@/store/SnackbarStore';
import * as Juce from 'juce-framework-frontend';

import Stack from '@mui/material/Stack';
import Button from '@mui/material/Button';

import LockOutlinedIcon from '@mui/icons-material/LockOutlined';
import MailOutlinedIcon from '@mui/icons-material/MailOutlined';

import TextField from '@mui/material/TextField';
import InputAdornment from '@mui/material/InputAdornment';

import { useForm, Controller } from 'react-hook-form';
import Typography from '@mui/material/Typography';
import { CompanyWebsite, PluginCode } from '@/define';
import { useState } from 'react';
import { useActivateStore } from '@/store/ActivateStore';
import Trial from './Trial';

type LoginFormValues = {
  userEmail: string;
  userPassword: string;
};

const visitWebsite = Juce.getNativeFunction('visitWebsite');
const setActivateJuce = Juce.getNativeFunction('setActivate');

export default function LoginForm() {
  const { setActivate, setOpen } = useActivateStore();
  const { enqueueSnackbar } = useSnackbarStore();
  const [loading, setLoading] = useState<boolean>(false);

  // 2. RHF useForm 설정
  const { handleSubmit, control, formState: { isSubmitting } } = useForm<LoginFormValues>({
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
      const res = await fetch(
        `${CompanyWebsite}/api/productActivation`,
        {
          method: 'POST',
          body: JSON.stringify({
            userEmail: values.userEmail,
            userPassword: values.userPassword,
            productCode: PluginCode
          }),
          cache: 'no-store'
        }
      ).then((res) => res.json().then((data) => ({ ok: res.ok, status: res.status, body: data })))
        .catch((err) => { // 서버 에러
          console.error(err);
        });
      if (res?.ok) {
        setActivateJuce(values.userEmail);
        setActivate(true);
        setOpen(false);
        enqueueSnackbar('Activate successful', { variant: 'success' });
      } else {
        enqueueSnackbar(res?.body.message, { variant: 'error' });
      }
      setLoading(false);
    } catch (err) {
      console.error(err);
      enqueueSnackbar('Unexpected error occurred', { variant: 'error' });
    }
  };

  return (
    <form onSubmit={handleSubmit(onSubmit)}>
      <Stack spacing={4}
      >
        <Controller
          name="userEmail"
          control={control}
          render={({ field }) => (
            <TextField
              {...field}
              label="Email"
              slotProps={{
                input: {
                  startAdornment: (
                    <InputAdornment position="start">
                      <MailOutlinedIcon fontSize="small" />
                    </InputAdornment>
                  )
                }
              }}
            />
          )}
        />

        <Controller
          name="userPassword"
          control={control}
          render={({ field }) => (
            <TextField
              {...field}
              type="password"
              label="Password"
              slotProps={{
                input: {
                  startAdornment: (
                    <InputAdornment position="start">
                      <LockOutlinedIcon fontSize="small" />
                    </InputAdornment>
                  )
                }
              }}
            />
          )}
        />

        <Typography
          textAlign="right"
          onClick={() => {
            visitWebsite(`${CompanyWebsite}/reset-password`);
          }}
          sx={{
            fontSize: 'var(--mui-fontSize-xs)'
          }}
        >
          Forgot password?
        </Typography>
        <Button
          loading={loading}
          type="submit"
          variant="contained"
          disabled={isSubmitting}
        >
          Sign in
        </Button>

        <Trial />
      </Stack>
    </form>
  );
}
