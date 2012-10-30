<?php

/**
 * Implements hook_token_info().
 */
function gsb_acquia_tokens_token_info() {
  $types['acquia'] = array(
    'name' => t("Acquia Environment Tokens"),
    'description' => t("Tokens from the acquia environment."),
  );

  // Specific environment variables.
  $acquia['site_name'] = array(
    'name' => t("Site Name"),
    'description' => t("The name of your site Ex. [environment]stg"),
  );
  $acquia['site_group'] = array(
    'name' => t("Site Group"),
    'description' => t("The subscription machine name. This is usually the same name as the account you ssh into the server with."),
  );
  $acquia['non_production'] = array(
    'name' => t("Non Production"),
    'description' => t("This is 1 if it's a production environment or 0 if it is not."),
  );
  $acquia['client_ip'] = array(
    'name' => t("Client IP Address"),
    'description' => t("The current IP address of the browser accessing the site."),
  );
  $acquia['site_environment'] = array(
    'name' => t("Site Environment"),
    'description' => t("The environment of the site. Ex. prod/test/dev"),
  );

  return array(
    'types' => $types,
    'tokens' => array(
      'acquia' => $acquia,
    ),
  );
}

/**
 * Implements hook_tokens().
 */
function gsb_acquia_tokens_tokens($type, $tokens, array $data = array(), array $options = array()) {
  global $user;

  $replacements = array();

  if ($type == 'acquia') {
    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'site_name':
          $replacements[$original] = $_ENV['AH_SITE_NAME'];
          break;
        case 'site_group':
          $replacements[$original] = $_ENV['AH_SITE_GROUP'];
          break;
        case 'site_environment':
          $replacements[$original] = $_ENV['AH_SITE_ENVIRONMENT'];
          break;
        case 'non_production':
          $replacements[$original] = $_ENV['AH_NON_PRODUCTION'];
          break;
        case 'client_ip':
          $replacements[$original] = $_ENV['AH_CLIENT_IP'];
          break;
      }
    }
  }

  return $replacements;
}
