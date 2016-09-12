<!-- template islandora-solr-wrapper.tpl.php -->
<?php $is_first_page = !(isset($_GET['page'])); ?>
<?php if (isset($messages)) { print $messages; } ?>

  <?php if (isset($tabs)): ?>
  <div class="tabs"><?php print render($tabs); ?></div>
  <?php endif; ?>
  <?php if (isset($action_links)): ?>
  <ul class="action-links">
    <?php print render($action_links); ?>
  </ul>
  <?php endif; ?>

  <?php if (isset($collection_page_metadata) && $is_first_page): ?>
    <div id="metadata-sidebar">
      <div class="islandora-basic-collection-metadata">
      <?php print $collection_page_metadata; ?>
      </div>
    </div>
  <?php endif; ?>
    <?php print render($title_prefix); ?>
    <?php if (isset($collection_tn_img) && $is_first_page): ?>
      <div class="islandora-basic-collection-metadata-image"> <?php print $collection_tn_img; ?> </div>
    <?php endif; ?>

  <?php
    if ($is_first_page && $is_collection) {
      $block = block_load('islandora_datastream_blocks', 'idb-DESC');
      $renderable_block = _block_get_renderable_array(_block_render_blocks(array($block)));
      print $renderable_block['islandora_datastream_blocks_idb-DESC']['#markup'];
    }
  ?>

<div class="islandora-solr-content">
  <div id="islandora-solr-top">
    <?php print $secondary_profiles; ?>
    <div id="islandora-solr-result-count">
      <?php print $islandora_solr_result_count; ?>
    </div>
  </div>

   <?php if ($page['sidebar']): ?>
     <?php print render($page['sidebar']); ?>
   <?php endif; ?>
  <div id="solr-search-results">
    <?php print $solr_pager; ?>
    <?php print $results; ?>
    <?php print $solr_debug; ?>
    <?php print $solr_pager; ?>
  </div>
</div>

</div><!-- /end main-content -->

