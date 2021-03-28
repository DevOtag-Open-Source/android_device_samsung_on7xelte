#ifndef INIT_SEC_H
#define INIT_SEC_H

#include <string.h>

#define TOTAL_VARIANTS 6 //Total number of variants

typedef struct {
    std::string model;
    std::string codename;
} variant;

static const variant G610F_model = {
    .model = "SM-G610F",
    .codename = "on7xeltedd"
};

static const variant G610L_model = {
    .model = "SM-G610L",
    .codename = "on7xeltekl"
};

static const variant G610K_model = {
    .model = "SM-G610K",
    .codename = "on7xeltekk"
};

static const variant G610S_model = {
    .model = "SM-G610S",
    .codename = "on7xelteks"
};

static const variant G610M_model = {
    .model = "SM-G610M",
    .codename = "on7xelteub"
};

static const variant G610Y_model = {
    .model = "SM-G610Y",
    .codename = "on7xeltezt"
};

static const variant *all_variants[TOTAL_VARIANTS] = {
    &G610F_model,
    &G610L_model,
    &G610K_model,
    &G610S_model,
    &G610M_model,
    &G610Y_model
};

#endif // INIT_SEC_H
