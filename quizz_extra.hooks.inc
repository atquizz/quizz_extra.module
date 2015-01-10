<?php

/**
 * Implements hook_schema_alter().
 */
function quizz_extra_schema_alter(&$schema) {
  $schema['quiz_entity']['fields']['comment'] = array(
      'description' => 'Whether comments are allowed on this quiz: 0 = no, 1 = closed (read only), 2 = open (read/write).',
      'type'        => 'int',
      'not null'    => TRUE,
      'default'     => 0,
  );
}

/**
 * Implements hook_enable().
 */
function quizz_extra_enable() {
  if (!db_field_exists('quiz_entity', 'comment')) {
    $spec = array('type' => 'int', 'not null' => TRUE, 'default' => 0);
    db_add_field('quiz_entity', 'comment', $spec);
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function quizz_extra_form_quiz_type_form_alter(&$form, $form_state) {
  $form['vtabs']['configuration']['comment'] = array(
      '#type'          => 'select',
      '#title'         => t('Comment'),
      '#default_value' => $form['#quiz_type']->getConfig('comment', 1),
      '#options'       => array(
          -1 => t('No comment'),
          0  => t('Close comment by default'),
          1  => t('Open comment by default'),
      ),
  );
}

/**
 * Implements hook_form_FORM_ID_alter()
 */
function quizz_extra_form_quiz_entity_form_alter(&$form, $form_state) {
  /* @var $quiz \Drupal\quizz\Entity\QuizEntity */
  $quiz = $form['#quiz'];

  // Comment feature is disabled on this quiz type.
  if (-1 == ($default_comment = $quiz->getQuizType()->getConfig('comment', 1))) {
    return;
  }

  $form['publishing']['comment_settings'] = array(
      '#type'        => 'fieldset',
      '#access'      => user_access('administer comments'),
      '#title'       => t('Comment settings'),
      '#collapsible' => TRUE,
      '#collapsed'   => TRUE,
      '#group'       => 'additional_settings',
      '#attributes'  => array('class' => array('comment-node-settings-form')),
      '#attached'    => array('js' => array(drupal_get_path('module', 'comment') . '/comment-node-form.js')),
      '#weight'      => 30,
      '#group'       => 'publishing_tabs',
  );

  $form['publishing']['comment_settings']['comment'] = array(
      '#type'          => 'radios',
      '#title'         => t('Comments'),
      '#title_display' => 'invisible',
      '#parents'       => array('comment'),
      '#default_value' => isset($quiz->comment) ? $quiz->comment : $default_comment,
      '#options'       => array(0 => t('Closed'), 1 => t('Open')),
  );
}

/**
 * Implements hook_entity_view().
 */
function quizz_extra_entity_view($entity, $type, $view_mode, $langcode) {
  $domain = variable_get('disqus_domain', '');
  if ($domain && ('quiz_entity' === $type)) {
    $uri = entity_uri($type, $entity);
    $entity->content['comment'] = array(
        '#type'   => 'disqus',
        '#disqus' => array(
            'domain'     => $domain,
            'status'     => (bool) $entity->comment,
            'url'        => url($uri['path'], array('absolute' => TRUE)),
            'title'      => $entity->label(),
            'identifier' => $type . '/' . $entity->identifier(),
            'developer'  => variable_get('disqus_developer', FALSE),
        ),
    );
  }
}
